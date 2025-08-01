import pino from "pino";

import winston from "winston";

function directConsole() {
    console.log(`xyxy: Conole log call makes log.`);
}

function pinoLogCall() {
    const logger = pino({
        level: process.env.LOG_LEVEL || 'info',
        base: { service: 'my-lambda' },
        timestamp: pino.stdTimeFunctions.isoTime,
    });

    logger.info('xyxyxy: Pino: Function started');
    logger.debug('xyxyxy: Pino: Detailed debug info', { foo: 'bar' });
    logger.error(new Error('xyxyxy: Pino: Something failed'));
}

function winstonLogCall() {
    const logger = winston.createLogger({
        level: 'info',
        format: winston.format.json(),
        defaultMeta: { service: 'user-service' },
        transports: [
            //
            // - Write all logs with importance level of `error` or higher to `error.log`
            //   (i.e., error, fatal, but not other levels)
            //
            new winston.transports.File({ filename: 'error.log', level: 'error' }),
            //
            // - Write all logs with importance level of `info` or higher to `combined.log`
            //   (i.e., fatal, error, warn, and info, but not trace)
            //
            new winston.transports.File({ filename: 'combined.log' }),
        ],
    });

    logger.info('xyxyxy: Winston: Function started');
    logger.debug('xyxyxy: Winston: Detailed debug info', { foo: 'bar' });
    logger.error(new Error('xyxyxy: Winston: Something failed'));
}

export default  function runLoggerTest() {
    directConsole();
    pinoLogCall();
    winstonLogCall();
}
