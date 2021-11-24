window.onload = function(){
    // async function test(url, method, body){
    //     const response = await fetch(url, {method, body:JSON.stringify(body)})
    //     console.log(response)
    // }
    var elems = document.querySelectorAll('.collapsible');
    var instances = M.Collapsible.init(elems);
    let calculate = document.getElementById("calculate");

    document.getElementById('quit').addEventListener('click', ()=>{
        document.cookie = "secret=; expires=Thu, 01 Jan 1970 00:00:00 UTC;"
        window.location = '/'
    })
    if(calculate != null){
        calculate.addEventListener('click', (e) =>{
            let max = document.getElementById("first").value
            let min = document.getElementById("second").value
            let data = {
                max, min
            }
            console.log(data)
            fetch("/", {
                method: 'POST',
                headers: {
                'Content-Type': 'application/json'
                },
                body: JSON.stringify(data)
            }).then(async (res) =>{
                let randomValue = await res.json()
                console.log(randomValue)
                document.getElementById("random").innerText = randomValue.random
            })
            .catch((error) => {
                console.log(error);
            });
            // test("http://localhost:3000/", "POST", {
            //     max, min
            // })
        })
    }
    if(document.getElementById('auth') != null){
        document.getElementById('auth').addEventListener('click', ()=>{
            let data = {
                email: document.querySelector('input[name="email"]').value, 
                pass: document.querySelector('input[name="pass"]').value
            }
            fetch("/login", {
                method: 'POST',
                headers: {
                'Content-Type': 'application/json'
                },
                body: JSON.stringify(data)
            }).then(async (res) =>{
                res = await res.json()
                console.log(res)
                if(res.redirect != undefined){
                    window.location = '/'
                }else{
                    M.toast({html: res.message, classes: 'rounded'});
                }
            })
            .catch((error) => {
                console.log(error);
            });
        })
    }
    
}