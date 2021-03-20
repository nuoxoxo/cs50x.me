const hex = [0,1,2,3,4,5,6,7,8,9,"a","b","c","d","e","f"];
const btn = document.getElementById('btn');
const color = document.querySelector(".color");

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
    
    for (let i = 0; i < 6; i++)
    {
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
