import config from '../config'

import { createServer as createHTTPServer } from 'http'
import { createServer as createNETServer } from 'net'
import { Server } from 'socket.io'

import game from './game'
import initializeController from './controller'
import initializeClient from './client'

import { getAdaptedData } from './adapters'

import EVENTS from './events'

const http = createHTTPServer()
const clientServer = new Server(http).on(
    EVENTS.CLIENT.CONNECT,
    client => {
        client.on(
            EVENTS.CLIENT.MOVEMENT,
            (direction: String) => game.emit(
                EVENTS.GAME.MOVEMENT,
                direction
            )
        )
    }
)
const controllerServer = createNETServer(
    controller => {
        game.on(
            EVENTS.GAME.MOVEMENT,
            direction => controller.write(direction)
        )

        controller.on(
            EVENTS.CONTROLLER.DATA,
            data => {
                const adapted = getAdaptedData(data)

                clientServer.emit(
                    adapted.key,
                    adapted.value
                )
            }
        )
    }
)

const initialize = () => {
    http.listen(config.clientPort)
    controllerServer.listen(config.controllerPort)

    initializeController()
    initializeClient()
}

initialize()