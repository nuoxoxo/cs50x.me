// Define UI vars
const form = document.querySelector('#task-form');
const taskInput = document.querySelector('#task');
const taskList = document.querySelector('.collection');
const clearBtn = document.querySelector('.clear-tasks');
const filter = document.querySelector('#filter');

// Load all event listeners
loadEventListeners();

function loadEventListeners() {

  // DOM Load event
  document.addEventListener('DOMContentLoaded', getTasks);

  // add task event
  form.addEventListener('submit', addTask);

  // remove task event
  taskList.addEventListener('click', removeTask);

  // clear task event
  clearBtn.addEventListener('click', clearTasks);

  // filter tasks event
  filter.addEventListener('keyup', filterTasks);

}

// Get Tasks from LS
function getTasks() {
  let tasks;
  if (localStorage.getItem('tasks') === null) {
    tasks = [];
  } else {
    tasks = JSON.parse(localStorage.getItem('tasks'));
  }


  tasks.forEach(function (task) {
    // Create li element
    // when push add task btn, will create li ele
    const li = document.createElement('li');
    li.className = 'collection-item';

    // create text node and append to li
    li.appendChild(document.createTextNode(task));

    // create new link element and add its class
    // delete task icon "x"
    const link = document.createElement('a');
    link.className = 'delete-item secondary-content';
    // secondary-contenet because itis an element to the right of a lisk item in materialize 

    // add icon html
    link.innerHTML = '<i class="fa fa-remove"></i>';

    // append the link to li
    li.appendChild(link);

    // append li to ul
    taskList.appendChild(li);
  });
}


// Add task 
// this function is event handler
// input e -> event object
function addTask(e) {
  if(taskInput.value == '') {
    // alert('Add a task');
    return false;
  }

  // Create li element
  // when push add task btn, will create li ele
  const li = document.createElement('li');
  li.className = 'collection-item';

  // create text node and append to li
  //li.appendChild(document.createTextNode(task)); <--- TYPO
  li.appendChild(document.createTextNode(taskInput.value));

  // create new link element and add its class
  // delete task icon "x"
  const link = document.createElement('a');
  link.className = 'delete-item secondary-content';
  // secondary-contenet because itis an element to the right of a lisk item in materialize 

  // add icon html
  link.innerHTML = '<i class="fa fa-remove"></i>';

  // append the link to li
  li.appendChild(link);

  // append li to ul
  taskList.appendChild(li);
  // console.log(li)

  // Store in Local Storage
  storeTaskInLocalStorage(taskInput.value);

  // clear input
  taskInput.value = '';

  e.preventDefault();
}


// Store Task
function storeTaskInLocalStorage(task) {
  let tasks;
  if (localStorage.getItem('tasks') === null) {
    tasks = [];
  } else {
    tasks = JSON.parse(localStorage.getItem('tasks'));
  }

  tasks.push(task);

  localStorage.setItem('tasks', JSON.stringify(tasks));
}

// Remove task
function removeTask(e) {
  if (e.target.parentElement.classList.contains('delete-item')) {
    // if (confirm('Are You Sure?')) {
      e.target.parentElement.parentElement.remove();

      // Remove from Local Storage
      removeTaskfromLocalStorage(e.target.parentElement.parentElement);

    // }
  }
}


// Remove from LS
function removeTaskfromLocalStorage(taskItem){
  let tasks;
  if (localStorage.getItem('tasks') === null) {
    tasks = [];
  } else {
    tasks = JSON.parse(localStorage.getItem('tasks'));
  }

  tasks.forEach(function(task, index){
    if(taskItem.textContent === task){
      tasks.splice(index, 1);

    }
  });

  localStorage.setItem('tasks', JSON.stringify(tasks));

}


// Clear tasks
function clearTasks() {

  // 1st way
  // taskList.innerHTML = '';

  // better
  // 2nd way: using a while loop
  while (taskList.firstChild) {
    taskList.removeChild(taskList.firstChild);
  }

  clearTasksFromLocalStorage();

}

// Clear Tasks from LS
function clearTasksFromLocalStorage() {
  localStorage.clear();
}

// Filter tasks
function filterTasks(e) {
  const text = e.target.value.toLowerCase();

  document.querySelectorAll('.collection-item').forEach(function (task) {
    const item = task.firstChild.textContent;
    if (item.toLowerCase().indexOf(text) != -1) {
      task.style.display = 'block';
    } else {
      task.style.display = 'none';

    }
  });
}