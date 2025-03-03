test this function:

 curl -X POST "https://c7rg55ylz9.execute-api.us-west-2.amazonaws.com/s2" \
     -H "Content-Type: application/json" \
     -d '{
           "name": "Alice"
         }'


{
  "resource": "/hello",
  "path": "/hello",
  "httpMethod": "POST",
  "body": "{\"name\": \"Alice\"}"
}


{
  "statusCode": 200,
  "headers": {
    "Content-Type": "application/json"
  },
  "body": "{\"message\": \"Hello, Alice!\"}"
}


