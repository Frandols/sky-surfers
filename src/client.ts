import { 
    app,
    BrowserWindow 
} from 'electron'

const createWindow = () => {
    const window = new BrowserWindow({
        width: 816,
        height: 700
    })

    window.loadFile(__dirname + '../../../public/index.html')

    if(!app.isPackaged) window.webContents.openDevTools()
}

const initializeClient = () => app.on(
    'ready',
    createWindow
)

export default initializeClient