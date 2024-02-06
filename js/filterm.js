filterSelectionmultiple("all")
var filter = [];

function filterSelectionmultiple(e){
  if (e === "all"){
    console.log(e);
    filter = [];
    return
  }
  if(filter.indexOf(e) === -1) {
      filter.push(e);
      console.log(filter);
      return
  }
  if(filter.indexOf(e) > -1) {
    var fil = filter.indexOf(e);
    filter.splice(fil, 1);
    console.log(filter);
  }
  var x, i;
  x = document.getElementsByClassName("filterDiv");
  if (e == "all") e = "";
  for (i = 0; i < x.length; i++) {
    RemoveClass(x[i], "show");
    if (x[i].className.indexOf(e) > -1) AddClass(x[i], "show");
  }
}

function AddClass(element, name) {
  var i, arr1, arr2;
  arr1 = element.className.split(" ");
  arr2 = name.split(" ");
  for (i = 0; i < arr2.length; i++) {
    if (arr1.indexOf(arr2[i]) == -1) {element.className += " " + arr2[i];}
  }
}

function RemoveClass(element, name) {
  var i, arr1, arr2;
  arr1 = element.className.split(" ");
  arr2 = name.split(" ");
  for (i = 0; i < arr2.length; i++) {
    while (arr1.indexOf(arr2[i]) > -1) {
      arr1.splice(arr1.indexOf(arr2[i]), 1);     
    }
  }
  element.className = arr1.join(" ");
}

// Add active class to the current button (highlight it)
var btnContainer = document.getElementById("myBtnContainer");
var btns = btnContainer.getElementsByClassName("btn");
for (var i = 0; i < btns.length; i++) {
  btns[i].addEventListener("click", function(){
    for (var c = 0; c < filter.length; c++) {
      this.className += " active";
      console.log(filter[c]);
    }
  });
}