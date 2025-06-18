
const jaegerRunner = require("./localjaegertest");

const handler = require("./index").handler;

jaegerRunner(handler);
