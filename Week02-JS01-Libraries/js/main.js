//####### Test JS vs. jQuery #######
//JavaScript
// var myListCollection = document.getElementsByTagName("ul");

// for(var i = 0; i < myListCollection.length; i++){
// 	if(myListCollection[i].className == "second"){
// 		myListCollection[i].childNodes[1].style.backgroundColor = "red";
// 	}
// }

// $("ul.second li:first-child").css("background-color", "blue");
//####### END Test JS vs. jQuery #######



//JS for CCLAB Session2
//To-Do List with jQuery and localStorage

//Array with all the tasks
var taskArray = [];

var updateLocalStorage = function(){
	var taskListString = JSON.stringify(taskArray);
	localStorage.setItem("taskArray", taskListString);
	console.log("taskListString = " + taskListString);
}

//function to display and update tasks
var displayTasks = function(){

	var taskListString = localStorage.getItem('taskArray');
	if(taskListString){
		taskArray = JSON.parse(taskListString);
	}

	// var taskListContainer = document.getElementById('taskList');
	// taskListContainer.innerHTML = '';

	//using jQuery
	$("#taskList").empty();

	// for(var i = 0; i<taskArray.length; i++){
	// 	console.log('task ' + i + ":" + taskArray[i]);

	// 	var newTask = document.createElement('div');

	// 	newTask.id = i;
	// 	newTask.className = 'task';

	// 	//paragraph inside our div
	// 	var task = document.createElement('p');

	// 	//insert our exsiting task-text into the paragraph
	// 	task.innerHTML = taskArray[i];

	// 	//create a delete button
	// 	var deleteButton = document.createElement('button');
	// 	deleteButton.id = "deleteButton";
	// 	//have text on delete button
	// 	deleteButton.innerHTML = "X";

	// 	deleteButton.addEventListener("click", function(e){
	// 		e.preventDefault();
	// 		deleteTask(e);

	// 	});

	// 	//add newly created elements to their parent
	// 	newTask.appendChild(task);
	// 	newTask.appendChild(deleteButton);
	// 	taskListContainer.appendChild(newTask);
	// };

	//using jQuery
	$(taskArray).each(function(i){

		var newTask = $('<div/>');
		newTask.attr('id', i).addClass("task").html("<p>" + this + "</p>");

		var deleteButton = $('<button/>');
		deleteButton.attr('id','deleteButton').text("X").click(function(e){
			e.preventDefault();
			deleteTask(e);
		});

		newTask.append(deleteButton);
		$('#taskList').append(newTask);
	});
}

//function to add a new task
var saveTask = function(){
	// var taskInput = document.getElementById('newTask');
	// var newTask = taskInput.value;

	//using jQuery
	var newTask = $('#newTask').val();

	//push this into our (empty) array
	taskArray.push(newTask);

	//clear the input field
	// taskInput.value = "";
	
	//using jQuery
	$('#newTask').val("");


	//insert new array into localStorage
	updateLocalStorage();

	//update the list
	displayTasks();

	//show us our array
	console.log(taskArray);

}

//function to delete a task
var deleteTask = function(e){
	//get the parent element's (=the task line's) id
	var taskNumber = e.target.parentElement.id;
	//delete the task from the array
	taskArray.splice(taskNumber,1);
	//update task list

	//insert new array into localStorage
	updateLocalStorage();

	displayTasks();
}

//main function that will include the event listener on the "add task button"
var init = function(){
	console.log("window loaded");

	// var addButton = document.getElementById('addButton');

	// addButton.addEventListener('click', function(e){
	// 	e.preventDefault();
	// 	saveTask();
	// });

	// in jQuery
	$('#addButton').click(function(e){
		e.preventDefault();
		saveTask();
	});

	displayTasks();	
}

//call this function when your html is loaded
// window.onload = init();

//jQuery version
$(document).ready(init);

