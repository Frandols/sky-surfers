import { 
    app,
    BrowserWindow 
} from 'electron'

import log from './logger'

const createWindow = () => {
    const window = new BrowserWindow({
        width: 814,
        height: 600
    })

    window.loadFile('../../public/index.html')
    window.webContents.openDevTools()

    log.info('Window opened')
}

const openWindow = () => app.on(
    'ready',
    createWindow
)

export default openWindow