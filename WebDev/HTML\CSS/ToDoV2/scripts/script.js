// Get references to the HTML elements that we'll interact with
const textInput = document.getElementById("textInput"); // The text input field where users type their tasks
const addButton = document.getElementById("addTask"); // The button to add a new task
const toDoList = document.getElementById("list"); // The unordered list where tasks will be displayed

// Function to add a new item to the to-do list
function addItem() {
  // Get the text input value, removing any leading or trailing spaces
  const userInput = textInput.value.trim();

  // If the input is empty, stop the function from proceeding
  if (userInput === "") {
    return;
  }

  // Create a new list item <li> for the task
  let newItem = document.createElement("li");
  newItem.textContent = userInput; // Set the task text to the value the user entered
  newItem.classList.add("listElement"); // Add the "listElement" class to style the task

  // Create a new button to remove the task
  let exitButton = document.createElement("button");
  exitButton.textContent = "X"; // Set the text of the button to "X"
  exitButton.classList.add("removeButton"); // Add the "removeButton" class for styling

  // Append the remove button to the new list item (so it appears inside the task item)
  newItem.appendChild(exitButton);

  // Add an event listener to the exit button to remove the task when clicked
  exitButton.addEventListener("click", function () {
    newItem.remove(); // Remove the list item from the DOM when the button is clicked
  });

  // Append the new task item (with its remove button) to the to-do list
  toDoList.appendChild(newItem);

  // Clear the input field after the task has been added
  textInput.value = "";
}

// Add an event listener to the add button to call addItem() when clicked
addButton.addEventListener("click", addItem);
