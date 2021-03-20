<img src="https://raw.githubusercontent.com/nuoxoxo/cs50x.me/main/week8/result_wide.jpg?raw=true" width=450>

homepage and trivia in 1

### counter
```html
<main>
  <div class="container">
    <span id="value">0</span>
    <div class="button-container">
      <button class="btn decrease">decrease</button>
      <button class="btn reset">reset</button>
      <button class="btn increase">increase</button>
    </div>
  </div>
</main>
<script src="app.js"></script>
```
```js
const value = document.querySelector("#value");
const btns = document.querySelectorAll(".btn");

let c = 0;

btns.forEach(function (btn) {
  btn.addEventListener("click", function(e) {
    const styles = e.currentTarget.classList;
    if (styles.contains("decrease")) {
      c--;
    } else if (styles.contains("increase")) {
      c++;
    } else {
      c = 0;
    }
    
    value.textContent = c;

    if (c > 0) {
      value.style.color = "green";
    }
    if (c < 0) {
      value.style.color = "red";
    }
    if (c == 0) {
      value.style.color = "#2E5897";
    }
  })
});
```
### flip
```html
<body>
  <nav>
    <div class="nav-center">
      <a href="../index-home.html">
        <button class="btn btn-back">back</button>
      </a>
    </div>
  </nav>
  <main>
    <div class="container">
      <button class="btn btn-flip" id="btn">
        <span class="color"></span>
      </button>
    </div>
  </main>
  <script src="app-flip.js"></script>
</body>
```
```js
const hex = [0,1,2,3,4,5,6,7,8,9,"a","b","c","d","e","f"];
const color = document.querySelector(".color");
const btn = document.getElementById('btn');

var num;
let hexColor = '#';
for (let i = 0; i < 6; i++){
  num = ranNum()
  hexColor += hex[num];
}

document.body.style.backgroundColor = hexColor;
color.textContent = hexColor;
color.style.color = hexColor;

btn.addEventListener('click', function(){  
  hexColor = '#';    
  for (let i = 0; i < 6; i++){
    num = ranNum()
    hexColor += hex[num];
  }
  document.body.style.backgroundColor = hexColor;
  color.textContent = hexColor;
  color.style.color = hexColor;
});

function ranNum(){
    return Math.floor(Math.random() * hex.length);
}
```
