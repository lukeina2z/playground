import awsServerlessExpress from "aws-serverless-express";
import webApp from "./src/webapi.mjs"

// const port = 3000;
// webApp.listen(port, () => {
//     console.log(`Server is running at http://localhost:${port}`);
// });

const server = awsServerlessExpress.createServer(webApp);
export const handler = (event, context) => {
  awsServerlessExpress.proxy(server, event, context);
};
