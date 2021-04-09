// Below: dynamically add del-buttons using event delegation

// Book constructor
function Book(title, author, isbn)
{
    this.title = title;
    this.author = author;
    this.isbn = isbn; 
}

// UI constructor
function UI(){}

UI.prototype.addBook = function(book)
{
    // <tbody> has an id of 'book-list'
    const list = document.getElementById('book-list');
    // create tr 
    const row = document.createElement('tr');
    // inster col into tr
    row.innerHTML = `
    <td>${book.title}</td>
    <td>${book.author}</td>
    <td>${book.isbn}</td>
    <td><a href='#' class='delete'>x</a></td>
    `;

    list.appendChild(row);
    
    console.log(row);
}

UI.prototype.deleteBook = function(target)
{
    if (target.className === 'delete')
    {
        // traverse the dom to get the parent of parent
        // target 'detele' > td > tr
        target.parentElement.parentElement.remove();
    }
}

UI.prototype.clear = function()
{
    document.getElementById('title').value = '';
    document.getElementById('author').value = '';
    document.getElementById('isbn').value = '';
};

UI.prototype.alert = function(msg, className)
{
    // create a div tag of 3 seconds
    const div = document.createElement('div');
    // the div tag will have a class of 'alert' another class of 'className'
    div.className = `alert ${className}`;
    div.appendChild(document.createTextNode(msg));

    // get parent
    // 'container' is a class (.---)
    const container = document.querySelector('.container'); 
    // '#book-form' is an id (#---)
    const form = document.querySelector('#u-full-width'); 
    container.insertBefore(div, form);

    setTimeout(function()
    {
        document.querySelector('.alert').remove();
    }, 3000);
}

// add event listeners
/// get book-form, listen on submit
document.getElementById('book-form').addEventListener('submit', function(e)
{
    const title = document.getElementById('title').value; 
    const author = document.getElementById('author').value; 
    const isbn = document.getElementById('isbn').value;
    
    const book = new Book(title, author, isbn);
    
    const ui = new UI();
    console.log(ui);

    if (title === '' || author ==='' || isbn ==='')
    {
        ui.alert('empty slots', 'error');
    } else
    {
        ui.addBook(book);
        ui.alert(`${title} by ${author} added successfully`, 'success');
        ui.clear();
    } 

    // console.log(book); 
    e.preventDefault();
});

document.getElementById('book-list').addEventListener('click', function(e)
{
    // same construction process as adding a table row
    // but a button is added this time
    const ui = new UI();
    ui.deleteBook(e.target);
    ui.alert(`Book removed`, 'success');

    e.preventDefault();
})
// 'book-list' is the parent class of the delete (button) class 
// why get the parent? 
// well when we click the button we want the whole row of <tr> gone