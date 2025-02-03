import serverless from "serverless-http"; 
import webApp from "./src/webapi.mjs"



// const port = 3000;
// webApp.listen(port, () => {
//     console.log(`Server is running at http://localhost:${port}`);
// });

export const handler = serverless(webApp);