import { keepPinging } from './ping';

console.log('Starting pingpong application...');

const urlFoo = process.env.URL || 'http://localhost:8080/aws-sdk-call';
const urlBar = 'http://localhost:8080/outgoing-http-call';

keepPinging(urlFoo, urlBar);