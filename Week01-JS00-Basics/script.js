//JS for CCLAB Session 1
//To-Do List with JS

//Array with all the tasks
var taskArray = [];

//function to display and update tasks
var displayTasks = function(){
	var taskListContainer = document.getElementById('taskList');
	taskListContainer.innerHTML = '';

	console.log(taskArray.length);
	for(var i = 0; i<taskArray.length; i++){
		console.log('task ' + i + ":" + taskArray[i]);

		var newTask = document.createElement('div');

		newTask.id = i;
		newTask.className = 'task';

		//paragraph inside our div
		var task = document.createElement('p');

		//insert our exsiting task-text into the paragraph
		task.innerHTML = taskArray[i];

		//create a delete button
		var deleteButton = document.createElement('button');
		deleteButton.id = "deleteButton";
		//have text on delete button
		deleteButton.innerHTML = "X";

		deleteButton.addEventListener("click", function(e){
			e.preventDefault();
			deleteTask(e);

		});

		//add newly created elements to their parent
		newTask.appendChild(task);
		newTask.appendChild(deleteButton);
		taskListContainer.appendChild(newTask);
	};
}

//function to add a new task
var saveTask = function(){
	var taskInput = document.getElementById('newTask');
	var newTask = taskInput.value;

	//push this into our (empty) array
	taskArray.push(newTask);

	//clear the input field
	taskInput.value = "";

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
	displayTasks();
}

//main function that will include the event listener on the "add task button"
var init = function(){
	console.log("window loaded");

	var addButton = document.getElementById('addButton');

	addButton.addEventListener('click', function(e){
		e.preventDefault();
		saveTask();
	});
}

//call this function when your html is loaded
window.onload = init();

