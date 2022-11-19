import config from '../config'

import { exec } from 'child_process'

const initializeController = () => {
    return exec(
        config.controllerPath,
        err => {
            if(err) process.exit(1)
        }
    )
}

export default initializeController