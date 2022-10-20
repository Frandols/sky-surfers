import config from '../config'

import { createServer as createHTTPServer } from 'http'
import { createServer as createNETServer } from 'net'
import { Server } from 'socket.io'

import openWindow from './window'

import log from './logger'

const http = createHTTPServer()

const client = new Server(http)
const controller = createNETServer(
    socket => {
        log.info('Controller connected')

        socket.on(
            'data',
            position => client.emit(
                'position',
                String(position)
            )
        )

        controller.on(
            'movement',
            direction => socket.write(direction)
        )
    }
)

client.on(
    'connect',
    socket => {
        log.info('Client connected')

        socket.on(
            'movement',
            direction => controller.emit(
                'movement',
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