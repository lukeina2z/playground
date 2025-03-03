test this function:

 curl -X POST "https://abc.execute-api.us-west-2.amazonaws.com/x1" \
     -H "Content-Type: application/json" \
     -d '{
           "orderId": "2",
           "amount": 98.6,
           "item": "bike"  
         }'