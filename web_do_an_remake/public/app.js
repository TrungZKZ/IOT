
// Get a database reference 
const databasedoam1 = database.ref('Doan/doam1');
const databasedoam2 = database.ref('Doan/doam2');
const databasedoam3 = database.ref('Doan/doam3');
const databasedoam4 = database.ref('Doan/doam4');

const databaserelay1 = database.ref('Doan/SetRelay/SetRelay1/SetRelay1');
const databaserelay2 = database.ref('Doan/SetRelay/SetRelay2/SetRelay2');
const databaserelay3 = database.ref('Doan/SetRelay/SetRelay3/SetRelay3');
const databaserelay4 = database.ref('Doan/SetRelay/SetRelay4/SetRelay4');

// Variables to save database current values

var doam1Reading;
var doam2Reading;
var doam3Reading;
var doam4Reading;

var relay1Reading;
var relay2Reading;
var relay3Reading;
var relay4Reading;

//////////////////////// nhận dữ liệu từ database //////////////////////////////
databasedoam1.on('value', (snapshot) => {
    doam1Reading = snapshot.val();
    console.log(doam1Reading);
    document.getElementById("reading-doam1").innerHTML = doam1Reading;
   }, (errorObject) => {
    console.log('The read failed: ' + errorObject.name);
   });
//---------------------------------------------------------------------------//
databasedoam2.on('value', (snapshot) => {
    doam2Reading = snapshot.val();
    console.log(doam2Reading);
    document.getElementById("reading-doam2").innerHTML = doam2Reading;
   }, (errorObject) => {
    console.log('The read failed: ' + errorObject.name);
   });
//---------------------------------------------------------------------------//
databasedoam3.on('value', (snapshot) => {
    doam3Reading = snapshot.val();
    console.log(doam3Reading);
    document.getElementById("reading-doam3").innerHTML = doam3Reading;
   }, (errorObject) => {
    console.log('The read failed: ' + errorObject.name);
   });
//---------------------------------------------------------------------------//
databasedoam4.on('value', (snapshot) => {
    doam4Reading = snapshot.val();
    console.log(doam4Reading);
    document.getElementById("reading-doam4").innerHTML = doam4Reading;
   }, (errorObject) => {
    console.log('The read failed: ' + errorObject.name);
   });

////////////////////////// nhận Relay từ database //////////////////////////////
    databaserelay1.on('value', (snapshot) => {
    relay1Reading = snapshot.val();
    console.log(relay1Reading);
    document.getElementById("reading-relay1").innerHTML = relay1Reading;
   }, (errorObject) => {
    console.log('The read failed: ' + errorObject.name);
   });
//---------------------------------------------------------------------------//
    databaserelay2.on('value', (snapshot) => {
    relay2Reading = snapshot.val();
    console.log(relay2Reading);
    document.getElementById("reading-relay2").innerHTML = relay2Reading;
   }, (errorObject) => {
    console.log('The read failed: ' + errorObject.name);
   });
//---------------------------------------------------------------------------//
   databaserelay3.on('value', (snapshot) => {
    relay3Reading = snapshot.val();
    console.log(relay3Reading);
    document.getElementById("reading-relay3").innerHTML = relay3Reading;
   }, (errorObject) => {
    console.log('The read failed: ' + errorObject.name);
   });
//---------------------------------------------------------------------------//
   databaserelay4.on('value', (snapshot) => {
    relay4Reading = snapshot.val();
    console.log(relay4Reading);
    document.getElementById("reading-relay4").innerHTML = relay4Reading;
   }, (errorObject) => {
    console.log('The read failed: ' + errorObject.name);
   });

//////////////////////// Nhận giá trị từ slider///////////////////////////////
var slider1 = document.getElementById("myRange1");
var output1 = document.getElementById("giatri1");
output1.innerHTML = slider1.value;
slider1.oninput = function() {
output1.innerHTML = this.value;}
//---------------------------------------------------------------------------//
var slider2 = document.getElementById("myRange2");
var output2 = document.getElementById("giatri2");
output2.innerHTML = slider2.value;
slider2.oninput = function() {
output2.innerHTML = this.value;}
//---------------------------------------------------------------------------//
var slider3 = document.getElementById("myRange3");
var output3 = document.getElementById("giatri3");
output3.innerHTML = slider3.value;
slider3.oninput = function() {
output3.innerHTML = this.value;}
//---------------------------------------------------------------------------//
var slider4 = document.getElementById("myRange4");
var output4 = document.getElementById("giatri4");
output4.innerHTML = slider4.value;
slider4.oninput = function() {
output4.innerHTML = this.value;}

/////////////////////////// hiển thị thời gian ////////////////////////////////
setInterval(myTimer, 1000);
function myTimer() {
  const d = new Date();
  document.getElementById("demo").innerHTML = d.toLocaleTimeString();
}

//////////////////////////// gửi dữ liệu đến relay ////////////////////////////
    function newData(uid) {
        var updates = {};
        switch (uid) {
            case 1:
            updates['Doan/relay1'] = {relay1: true};
                break;
            case 2:
            updates['Doan/relay2'] = {relay2: true};
                break;
            case 3:
            updates['Doan/relay3'] = {relay3: true};
                break;
            case 4:
            updates['Doan/relay4'] = {relay4: true};
                break;
            default:
                break;
        }
        return firebase.database().ref().update(updates);
    }

//////////////////////////// gửi dữ liệu đến relay ////////////////////////////
function SetRelay(relayid) {
    var updates = {};
    switch (relayid) {
        case 1:
        var set1 = parseInt(document.getElementById('myRange1').value, 10);
        updates['Doan/SetRelay/SetRelay1'] = {SetRelay1: set1};
            break;
        case 2:
        var set2 = parseInt(document.getElementById('myRange2').value, 10);
        updates['Doan/SetRelay/SetRelay2'] = {SetRelay2: set2};
            break;
        case 3:
        var set3 = parseInt(document.getElementById('myRange3').value, 10);
        updates['Doan/SetRelay/SetRelay3'] = {SetRelay3: set3};
            break;
        case 4:
        var set4 = parseInt(document.getElementById('myRange4').value, 10);
        updates['Doan/SetRelay/SetRelay4'] = {SetRelay4: set4};
            break;
        default:
            break;
    }
    return firebase.database().ref().update(updates);
}

