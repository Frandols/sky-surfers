import config from '../config'

import { createServer as createHTTPServer } from 'http'
import { createServer as createNETServer } from 'net'
import { Server } from 'socket.io'

import openWindow from './window'

import log from './logger'

let movement: 'left' | 'right' | 'none' = 'none'
let position: number = 0

const http = createHTTPServer()
const net = createNETServer(
    socket => {
        log.info('Controller connected')

        socket.on(
            'data',
            data => {
                const payload = Number(data)

                if(position !== payload) {
                    position = payload

                    log.info(`Position updated: ${position}`)

                    client.emit(
                        'data',
                        position
                    )
                }

                socket.write(movement)

                if(movement !== 'none') {
                    movement = 'none'
                }
            }
        )
    }
)

const client = new Server(http)

client.on(
    'connect',
    socket => {
        log.info('Client connected')

        socket.on(
            'data',
            data => {
                if(data === 'left' || data === 'right') {
                    movement = data
                }
            }
        )

        client.on(
            'position',
            () => {
                console.log('ACA')
            }
        )
    }
)

const init = () => {
    http.listen(
        config.clientPort,
        () => log.info(`Client server enabled: http://${config.host}:${config.clientPort}`)
    )

    net.listen(
        config.controllerPort,
        () => {
            log.info(`Controller server enabled: http://${config.host}:${config.controllerPort}`)
        }
    )
    
    openWindow()
}

init()