import { exec } from 'child_process'

import { 
    app,
    BrowserWindow 
} from 'electron'

import log from './logger'

const createWindow = () => {
    const window = new BrowserWindow({
        width: 816,
        height: 700
    })

    window.loadFile('../../public/index.html')

    log.info('Window opened')
}

const openWindow = () => app.on(
    'ready',
    createWindow
)

export default openWindow