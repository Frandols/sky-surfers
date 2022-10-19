"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const electron_1 = require("electron");
const logger_1 = __importDefault(require("./logger"));
const createWindow = () => {
    const window = new electron_1.BrowserWindow({
        width: 800,
        height: 600
    });
    window.loadFile('../../public/index.html');
    window.webContents.openDevTools();
    logger_1.default.info('Window opened');
};
const openWindow = () => electron_1.app.on('ready', createWindow);
exports.default = openWindow;
