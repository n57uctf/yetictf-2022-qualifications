
$('.btn').click(function() {
    console.log('doing shit')
    $("h1").toggle()
    $("h3").toggle()
    $("h4").toggle()
    $("h5").toggle()
    $(".logo").toggle()
    $("input").toggle()
    $("button").toggle()
    // $(".container").toggle()
    $(".test").toggle()
    // if ($(".test").is(":visible")) {
    // }
    console.log('done')
})

if ($(location).attr('href').includes('link')) {
    console.log("YAYAY")
    $(".test").toggle()

}

// $(window).on('hashchange', function(e){
//     console.log('rendered')

//     $(".test").toggle()
    
//     // do something...
// });

// $('h4').on(function() {
// })

// $('h4').ready(function() {
//     console.log('rendered')
//     $(".test").toggle()
// })
// <style>
//   #loading-image {
    // visibility: hidden;
//   }
// </style>
