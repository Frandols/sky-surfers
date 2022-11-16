import path from 'path'
import { exec } from 'child_process'

import { 
    app,
    BrowserWindow 
} from 'electron'

import log from './logger'

const createWindow = () => {
    const executablePath = 'main.exe'
    exec(
        executablePath,
        err => {
            if(err) process.exit(1)
        }
    )

    const window = new BrowserWindow({
        width: 816,
        height: 700
    })

    window.loadFile('../../public/index.html')
    window.webContents.openDevTools()

    window.on(
        'resize',
        () => console.log(window.getSize())
    )

    log.info('Window opened')
}

const openWindow = () => app.on(
    'ready',
    createWindow
)

export default openWindow