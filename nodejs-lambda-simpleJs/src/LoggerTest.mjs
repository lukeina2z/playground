import pino from "pino";

import winston from "winston";

function directConsole() {
    console.log(`xyxy: Conole log call makes log.`);
}

function pinoLogCall() {
    const logger = pino({
        level: process.env.LOG_LEVEL || 'debug',
        base: { service: 'my-lambda' },
        timestamp: pino.stdTimeFunctions.isoTime,
    });

    logger.info('xyxyxy: Pino: Function started');
    logger.debug('xyxyxy: Pino: Detailed debug info', { foo: 'bar' });
    logger.error(new Error('xyxyxy: Pino: Something failed'));
}

function winstonLogCall() {
    const logger = winston.createLogger({
        level: 'debug',
        format: winston.format.json(),
        defaultMeta: { service: 'nodejs-lambda-fn-01' },
        transports: [
            new winston.transports.Console(), // <— must add this to log to stdout
        ],
    });

    logger.info('xyxyxy: Winston: Function started');
    logger.debug('xyxyxy: Winston: Detailed debug info', { foo: 'bar' });
    logger.error(new Error('xyxyxy: Winston: Something failed'));
}

export default function runLoggerTest() {
    directConsole();
    pinoLogCall();
    winstonLogCall();
}
