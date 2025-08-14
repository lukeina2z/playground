# PingPong

A TypeScript Node.js project that pings web endpoints at regular intervals.

## Features

- `pingWeb`: Fetches content from a website and returns status information
- `keepPinging`: Continuously pings a URL 10 times per second
- TypeScript support with automatic rebuilding
- ESLint for code linting
- Jest for unit testing
- Graceful shutdown handling

## Installation

```bash
npm install
```

## Usage

### Development (with auto-rebuild)
```bash
npm run dev
```

### Production
```bash
npm run build
npm start
```

### Testing
```bash
npm test
```

### Linting
```bash
npm run lint
npm run lint:fix
```

## Scripts

- `npm run build` - Compile TypeScript to JavaScript
- `npm run start` - Run the compiled application
- `npm run dev` - Run in development mode with auto-rebuild
- `npm test` - Run unit tests
- `npm run lint` - Check code style
- `npm run lint:fix` - Fix linting issues automatically