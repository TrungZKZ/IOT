/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////// Nhận dữ liệu //////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Get a database reference 
const databasetemp = [];
const databasedoam = [];



for (let i = 1; i <= 20; i++) {
    databasetemp[i] = database.ref(`Nhom11/temperature_arr/${i}`);
    databasedoam[i] = database.ref(`Nhom11/humidity_arr/${i}`);
}

const databaseTempRef = database.ref('Nhom11/temperature');
const databaseDoamRef = database.ref('Nhom11/humidity');

// Variables to save database current values

var doamReading = new Array(21);
var tempReading = new Array(21);
var sum1;
var sum2;
var tempReading;
var doamReading;

//////////////////////// nhận dữ liệu từ database //////////////////////////////
//--------------------------đến table2(nội dung 5)----------------------------//
for (let i = 1; i <= 20; i++) {
  databasetemp[i].on('value', (snapshot) => {
    tempReading[i] = snapshot.val();
    sum2 += tempReading[i];
    console.log(tempReading[i]);
    document.getElementById(`reading-temp${i}`).innerHTML = tempReading[i];
  }, (errorObject) => {
    console.log('The read failed: ' + errorObject.name);
  });
}

var total = tempReading.reduce(function(sum, value) {
  return sum + value;
}, 0);
var averageTemp = total / tempReading.length;
// In giá trị trung bình ra HTML
document.getElementById('average-temp').innerHTML = averageTemp;

//---------------------------------------------------------------------------//
for (let i = 1; i <= 20; i++) {
  databasedoam[i].on('value', (snapshot) => {
    doamReading[i] = snapshot.val();
    sum1 += doamReading[i];
    console.log(doamReading[i]);
    document.getElementById(`reading-doam${i}`).innerHTML = doamReading[i];
  }, (errorObject) => {
    console.log('The read failed: ' + errorObject.name);
  });
}

var total = doamReading.reduce(function(sum, value) {
  return sum + value;
}, 0);
var averageHumidity = total / doamReading.length;
// In giá trị trung bình ra HTML
document.getElementById('average-humidity').innerHTML = averageHumidity;

//----------------------đến table1 và slider(nội dung4)-----------------------//
databaseTempRef.on('value', (snapshot) => {
  tempReading = snapshot.val();
  console.log(tempReading);
  document.getElementById('reading-temp').innerHTML = tempReading;
  document.getElementById('reading-temp22').innerHTML = tempReading;
  document.getElementById('reading-temp11').innerHTML = tempReading;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});
//---------------------------------------------------------------------------//
databaseDoamRef.on('value', (snapshot) => {
  doamReading = snapshot.val();
  console.log(doamReading);
  document.getElementById('reading-doam').innerHTML = doamReading;
  document.getElementById('reading-doam22').innerHTML = doamReading;
  document.getElementById('reading-doam11').innerHTML = doamReading;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});
//-------------------------Tính trung bình(nội dung6)-----------------------//



function checkTemperature() {
  var threshold = document.getElementById('threshold').value;
  var alertDot = document.getElementById('alert-dot');
  if (tempReading > threshold) {
    alertDot.style.backgroundColor = "red";
  } else {
    alertDot.style.backgroundColor = "green";
  }
}

function updateThresholdValue() {
  var threshold = document.getElementById('threshold').value;
  document.getElementById('threshold-value').innerHTML = threshold;
}

// Call the function once to initialize the displayed threshold value
updateThresholdValue();
function checkTemperature() {
  var threshold = document.getElementById('threshold').value;
  var alertDot = document.getElementById('alert-dot');
  if (tempReading > threshold) {
  alertDot.style.backgroundColor = "red";
  } else {
  alertDot.style.backgroundColor = "blue";
  }
  }