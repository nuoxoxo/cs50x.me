document.addEventListener('DOMContentLoaded', function(){

    let correct = document.querySelectorAll('.cor');
    for (let i = 0; i < correct.length; i++)
    {
        correct[i].addEventListener('click', function(){
            if (correct[i].style.backgroundColor != 'lightGreen'){
                correct[i].style.backgroundColor = 'lightGreen';
            }

            if (correct[i].style.backgroundColor == 'lightGreen'){
            correct[i].style.backgroundColor = 'None';
            }
        // correct[i].style.backgroundColor = 'lightGreen';
        // document.querySelector('#feedback1').innerHTML = 'Correct!';
    });
    }

    let incorrects = document.querySelectorAll('.inc');
    for (let i = 0; i < incorrects.length; i++)
    {
        incorrects[i].addEventListener('click', function(){
        incorrects[i].style.backgroundColor = 'pink';
        // document.querySelector('#feedback2').innerHTML = 'Incorrect';
    });
    }

    document.querySelector('#check').addEventListener('click', function()
    {
        let input = document.querySelector('input');
        if  (input.value === "Moordale High")
        {
            input.style.backgroundColor = 'lightgreen';
        }else
        {
            input.style.backgroundColor = 'pink';
        }
    });



    

});