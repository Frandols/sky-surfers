import config from '../config'

import { createServer as createHTTPServer } from 'http'
import { createServer as createNETServer } from 'net'
import { Server } from 'socket.io'

import initializeController from './controller'

import openWindow from './window'

import { getAdaptedData } from './adapters'

import log from './logger'

import EVENTS from './events'

const http = createHTTPServer()

const client = new Server(http)
const controllers = createNETServer(
    socket => {
        log.info('Controllers connected')

        controllers.on(
            EVENTS.CONTROLLER.MOVEMENT,
            direction => socket.write(direction)
        )

        socket.on(
            EVENTS.CONTROLLER.DATA,
            data => {
                const adapted = getAdaptedData(String(data))

                client.emit(
                    adapted.key,
                    adapted.value
                )
            }
        )
    }
)

client.on(
    EVENTS.CLIENT.CONNECT,
    socket => {
        log.info('Client connected')

        socket.on(
            EVENTS.CLIENT.MOVEMENT,
            (direction: String) => controllers.emit(
                EVENTS.CONTROLLER.MOVEMENT,
                direction
            )
        )
    }
)

const init = async () => {
    await http.listen(
        config.clientPort,
        () => log.info(`Client server enabled: http://${config.host}:${config.clientPort}`)
    )

    await controllers.listen(
        config.controllerPort,
        () => {
            log.info(`Controllers server enabled: http://${config.host}:${config.controllerPort}`)
        }
    )
    
    const controllerInitialization = initializeController()

    controllerInitialization.on(
        'spawn',
        () => {
            log.info('Controllers available')

            openWindow()
        }
    )
}

init()