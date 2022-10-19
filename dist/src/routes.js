"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const path_1 = __importDefault(require("path"));
const logger_1 = __importDefault(require("./logger"));
const enableRoutes = (app) => {
    app.get('/', (_, res) => res.sendFile(path_1.default.join(__dirname, '../../public/index.html')));
    logger_1.default.info('Routes enabled');
};
exports.default = enableRoutes;
