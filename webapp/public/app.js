// Database Paths
var dataFloatPath = 'test/float';
var dataIntPath = 'test/int';
var dataStringPath = 'test/string';
// Get a database reference 
const databaseFloat = database.ref(dataFloatPath);
const databaseInt = database.ref(dataIntPath);
const databaseString = database.ref(dataStringPath);
// Variables to save database current values
var floatReading;
var intReading;
var stringReading;

// Attach an asynchronous callback to read the data
databaseFloat.on('value', (snapshot) => {
 floatReading = snapshot.val();
 console.log(floatReading);
 document.getElementById("reading-float").innerHTML = floatReading;
}, (errorObject) => {
 console.log('The read failed: ' + errorObject.name);
});
////////////////////////////////////////////////////////
databaseInt.on('value', (snapshot) => {
 intReading = snapshot.val();
 console.log(intReading);
 document.getElementById("reading-int").innerHTML = intReading;
}, (errorObject) => {
 console.log('The read failed: ' + errorObject.name);
});
////////////////////////////////////////////////////////
databaseString.on('value', (snapshot) => {
    stringReading = snapshot.val();
    console.log(stringReading);
    document.getElementById("reading-string").innerHTML = stringReading;
   }, (errorObject) => {
    console.log('The read failed: ' + errorObject.name);
   });
////////////////////////////////////////////////////////
