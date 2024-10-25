const fs = require('fs');
const readline = require('readline');
const aliases = require('./keycodeAliases.json');

/**
 * TODO
 *  - [ ] rename to something that makes more sense
 *  - [ ] read only the lines for 10u
 *  - [ ] replace the startsWith/endsWith usage with regex
 *  - [ ] probably move this into its own directory so I can have Yarn files, etc.
 *  - [ ] clean up/consolidate unused codes in btgrant-76.h
 *  - [ ] double-check the width of all columns, especially the first
 */

const badlyNamedThings = ['HRM']

const layers = { // TODO build this up at startup; or put this in a JSON file
    // varName: 'BASE',
    BASE: {
        name: 'Base',
        1: [],
        2: [],
        3: [],
        THUMB: []
    },
    NUM: {
        name: 'Number',
        1: [],
        2: [],
        3: [],
        THUMB: []
    },
    SYM: {
        name: 'Symbol',
        1: [],
        2: [],
        3: [],
        THUMB: []
    },
    NAV: {
        name: 'Navigation',
        1: [],
        2: [],
        3: [],
        THUMB: []
    },
    FUN: {
        name: 'Function',
        1: [],
        2: [],
        3: [],
        THUMB: []
    },
    MSE: {
        name: 'Mouse Keys',
        1: [],
        2: [],
        3: [],
        THUMB: []
    },
    ADD: {
        name: 'Additional Features',
        1: [],
        2: [],
        3: [],
        THUMB: []
    }
}

const fileStream = fs.createReadStream('./users/btgrant-76/btgrant-76.h');

const rl = readline.createInterface({
    input: fileStream,
    crlfDelay: Infinity  // Recognize all instances of CR LF ('\r\n') as a single line break
});

let stopProcessing = false;

const findLayer = varName => {
    for (const layer in layers) {
        // console.log(layer);
        if (varName.includes(layer)) {
            return layer
        }
    }
    console.log('unidentified layer!', varName) //
    return null

    // throw new Error(`Unidentified layer: ${varName}`)
    // return 'UNIDENTIFIED' // TODO throw an error?
}

const splitDefineLine = line => {
    const splits = line.split(' ').filter(w => w.length > 0)

    const commentIndex = splits.indexOf('//')

    if (commentIndex !== -1) {
        return splits.slice(0, commentIndex)
    }

    return splits
}

const processKeyCodes = keycodes => {
    const updatedKeycodes = keycodes.flatMap(kc => {
        kc = kc.replace(',', '')

        if (aliases[kc]) {
            return aliases[kc].split(',') // FIXME this splits the alias ", <"
        }

        if (kc.startsWith('KC_')) {
            return kc.replace('KC_', '')
        }

        return kc
    })

    return updatedKeycodes
}

const RIGHT_PAD = 6
const CELL_WIDTH = 8 // the  full width of the keycode cell

const processDefine = line => {
    const splits = splitDefineLine(line)
    const varName = splits[1]
    if (varName.startsWith('___')) {
        const layerId = findLayer(varName)

        if (!layerId) {
            console.log('skipping', layerId)
            return
        }

        const splitVarName = varName.split('_').filter(w => w.length > 0)

        const rowId = splitVarName[1]
        const keycodes = processKeyCodes(splits.slice(2)).map(kc => kc.padEnd(RIGHT_PAD/*, '_'*/).padStart(CELL_WIDTH/*, '_'*/))
        console.log('layer define', layerId, rowId, keycodes)

        // TODO refactor the following lines
        const layer = layers[layerId]
        const row = layer[rowId]
        layers[layerId][rowId] = row.concat(keycodes)
    } else if (line.includes('//:')) { // define with an alias
        const keycode = splits[1]
        console.log('found alias', keycode)
        const alias = splits[splits.length - 1].replace('//:', '').replace('_', ' ')
        if (keycode.includes(',')) {

        } else {
            aliases[keycode] = alias
        }
    } else {
        // console.log('ordinary define', line);
    }
}

const processLine = rawLine => {
    const trimmed = rawLine.trim();
    if (trimmed.length === 0) {
        return
    }
    if (!stopProcessing) {
        if (trimmed.startsWith('/** 12u **/')) {
            stopProcessing = true
        } else if ((trimmed.startsWith('/* ') && trimmed.endsWith(' */')) || trimmed.startsWith('//')) {
            // console.log('comment', trimmed)
        } else if (trimmed.startsWith('#define')) {
            processDefine(trimmed)
        } else {
            console.log('processing', trimmed)
        }
    } else {
        // console.log('stopped', trimmed)
    }
}


rl.on('line', (line) => {
    // if (line.startsWith('/** 12u **/'))
    // console.log(line);
    processLine(line)
});

const generateDivider = () => `|${Array(10).fill(''.padStart(CELL_WIDTH, '-')).join('+')}|`

const wrapRow = row => {
    return `|${row.join('|')}|`
}

rl.on('close', () => {
    console.log('finished', aliases)

    // TODO split all these down the middle
    for (const layer in layers) {
        const l = layers[layer]

        const sectionTitle = `#### ${l.name} (\`${layer}\`)\n`
        console.log(sectionTitle)
        console.log('```text')
        const lOne = l[1]
        const lTwo = l[2]
        const lThree = l[3]
        const lThumb = l['THUMB']

        const leftThumbPadding = Array(2).fill(''.padStart(CELL_WIDTH, ' '))

        const divider = generateDivider() // TODO parameterize this so it can be used for the thumb row, too
        console.log(divider)
        console.log(wrapRow(lOne))
        console.log(divider)
        console.log(wrapRow(lTwo))
        console.log(divider)
        console.log(wrapRow(lThree))
        console.log(divider)
        console.log(`${leftThumbPadding.join(' ')} ${wrapRow(lThumb)}`)

        console.log('```\n')
    }

    console.log('File reading completed.');
});
