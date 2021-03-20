let counter = 0;
// select value and buttons
const value = document.querySelector("#value");
const btns = document.querySelectorAll(".btn");

btns.forEach(function (btn) {
  btn.addEventListener("click", function (e) {
    const styles = e.currentTarget.classList;
    if (styles.contains("decrease")) {
      counter--;
    } else if (styles.contains("increase")) {
      counter++;
    } else {
      counter = 0;
    }
    value.textContent = counter;

    if (counter > 0) {
      value.style.color = "green";
    }
    if (counter < 0) {
      value.style.color = "red";
    }
    if (counter == 0) {
      value.style.color = "#2E5897";
    }
  })
});