import { myHandler  } from "./myHandler.mjs";

// Remove testing call in Lambda
const test = async () => {
    const rsp = await myHandler({}, {});
    console.log("Done");
}
test();
// Remove testing call in Lambda

export { myHandler };

