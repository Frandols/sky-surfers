import config from '../config'

import { createServer as createHTTPServer } from 'http'
import { createServer as createNETServer } from 'net'
import { Server } from 'socket.io'

import openWindow from './window'

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
            EVENTS.CONTROLLER.POSITION,
            position => client.emit(
                EVENTS.CLIENT.POSITION,
                String(position)
            )
        )
    }
)

client.on(
    'connect',
    socket => {
        log.info('Client connected')

        socket.on(
            EVENTS.CLIENT.MOVEMENT,
            direction => controller.emit(
                EVENTS.CONTROLLER.MOVEMENT,
                direction === 'left' || direction === 'right'
                ? direction
                : 'none'
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