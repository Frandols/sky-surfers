"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const config_1 = __importDefault(require("../config"));
const http_1 = require("http");
const net_1 = require("net");
const socket_io_1 = require("socket.io");
const window_1 = __importDefault(require("./window"));
const logger_1 = __importDefault(require("./logger"));
let movement = 'none';
let position = 0;
const http = (0, http_1.createServer)();
const net = (0, net_1.createServer)(socket => {
    logger_1.default.info('Controller connected');
    socket.on('data', data => {
        const payload = Number(data);
        if (position !== payload) {
            position = payload;
            logger_1.default.info(`Position updated: ${position}`);
            client.emit('data', position);
        }
        socket.write(movement);
        if (movement !== 'none') {
            movement = 'none';
        }
    });
});
const client = new socket_io_1.Server(http);
client.on('connect', socket => {
    logger_1.default.info('Client connected');
    socket.on('data', data => {
        if (data === 'left' || data === 'right') {
            movement = data;
        }
    });
    client.on('position', () => {
        console.log('ACA');
    });
});
const init = () => {
    http.listen(config_1.default.clientPort, () => logger_1.default.info(`Client server enabled: http://${config_1.default.host}:${config_1.default.clientPort}`));
    net.listen(config_1.default.controllerPort, () => {
        logger_1.default.info(`Controller server enabled: http://${config_1.default.host}:${config_1.default.controllerPort}`);
    });
    (0, window_1.default)();
};
init();
