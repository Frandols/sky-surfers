import path from 'path'

import { exec } from 'child_process'

const executablePath = path.join(__dirname + '../../../')

const initializeController = () => {
    exec(
        `cd ${executablePath} && main.exe`,
        err => {
            if(err) throw new Error(err.message)
        }
    )
}

export default initializeController