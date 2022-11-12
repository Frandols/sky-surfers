import config from '../config'

import { createServer as createHTTPServer } from 'http'
import { createServer as createNETServer } from 'net'
import { Server } from 'socket.io'

import openWindow from './window'

import { getAdaptedData } from './adapters'

import log from './logger'

import EVENTS from './events'

const http = createHTTPServer()

const client = new Server(http)
const controller = createNETServer(
    socket => {
        log.info('Controller connected')

        controller.on(
            EVENTS.CONTROLLER.MOVEMENT,
            direction => socket.write(direction)
        )

        socket.on(
            EVENTS.CONTROLLER.DATA,
            data => {
                const adapted = getAdaptedData(String(data))

                switch(adapted.key) {
                    case 'position':
                        return client.emit(
                            EVENTS.CLIENT.POSITION,
                            adapted.value
                        )
                    case 'enemy':
                        return log.info('Enemigo desplegado')
                    case 'atack':
                        return log.info('Ataque recibido')
                    default:
                        return
                }
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
            (direction: String) => controller.emit(
                EVENTS.CONTROLLER.MOVEMENT,
                direction
            )
        )
    }
)

const init = () => {
    http.listen(
        config.clientPort,
        () => log.info(`Client server enabled: http://${config.host}:${config.clientPort}`)
    )

    controller.listen(
        config.controllerPort,
        () => {
            log.info(`Controller server enabled: http://${config.host}:${config.controllerPort}`)
        }
    )
    
    openWindow()
}

init()