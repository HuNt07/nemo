import { HfInference } from '@huggingface/inference'
import dotenv from "dotenv";
import { json } from 'stream/consumers';

dotenv.config()

const TOKEN = process.env.API   
const inference = new HfInference(TOKEN)

// function to merge key, value and make an object
function convertToObj(labels, ans) {   
  let obj = {};
  labels.forEach((k, i) => 
            { obj[k] = ans[i] })
  return obj; 
}
// function to map values 
function getObjectKey(obj, value) {
  return Object.keys(obj).find(key => obj[key] === value);
}

async function doZeroShot(input){
  let prediction = await inference.zeroShotClassification({
    model: 'facebook/bart-large-mnli',
    inputs: [
      input
    ],
    parameters: { candidate_labels: ['sad', 'happy', 'neutral', 'astonished', 'cry'] }
    
})

let test = prediction[0];
let labels = test["labels"];
let ans = test["scores"];
 

let finals = convertToObj(labels, ans)

// console.log(finals)

let arr = Object.values(finals);
let max = Math.max(...arr);



console.log(getObjectKey(finals, max));
return getObjectKey(finals,max)
}

export {doZeroShot}