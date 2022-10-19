"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var config;
(function (config) {
    config["host"] = "localhost";
    config[config["controllerPort"] = 3000] = "controllerPort";
    config[config["clientPort"] = 5000] = "clientPort";
})(config || (config = {}));
exports.default = config;
