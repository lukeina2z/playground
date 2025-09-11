import { myHandler } from "./autoInstrumentOnly.mjs";

// Remove testing call in Lambda
const test = async () => {
    const rsp = await myHandler({}, {});
    console.log("Done");
}

test();

export { myHandler };

