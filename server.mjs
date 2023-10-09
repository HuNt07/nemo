// Import required modules
import express from 'express';
import path from 'path';
import {doZeroShot} from './zeroshot.js'
import { fileURLToPath } from 'url'; 

const __filename = fileURLToPath(import.meta.url);

const __dirname = path.dirname(__filename);
// Create an Express app
const app = express();
const port = process.env.PORT || 3000;

app.use(express.json())


// // Define the static file directory
const publicDirectoryPath = path.join(__dirname, '/');

// // Serve static files (e.g., index.html)
app.use(express.static(publicDirectoryPath));
app.get('/', function(req, res) {
  res.sendFile('index.html', { root: __dirname });
});

app.post('/feeling',function(req, res) {
  console.log(req.body.userinput)
  doZeroShot(req.body.userinput).then((data)=>{
    console.log('data is '+data)
    let result = {
      "feeling":data
    }
    console.log(result)
    res.send(result)
  })

});

// Start the server
app.listen(port, () => {
  console.log(`Server is running on port ${port}`);
});