"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const config_1 = __importDefault(require("../config"));
// import { WebSocketServer } from 'ws'
const net_1 = require("net");
const logger_1 = __importDefault(require("./logger"));
var EVENTS;
(function (EVENTS) {
    EVENTS["CONNECTION"] = "connection";
    EVENTS["DATA"] = "data";
})(EVENTS || (EVENTS = {}));
const enableSockets = () => {
    const server = (0, net_1.createServer)(socket => {
        socket.on(EVENTS.CONNECTION, () => logger_1.default.info('Socket connected'));
    });
    server.listen(3001, config_1.default.host, () => logger_1.default.info('Sockets enabled'));
};
exports.default = enableSockets;
