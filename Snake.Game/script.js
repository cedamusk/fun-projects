//Initialize canvas and context
const canvas=document.getElementById('gameCanvas');
const ctx=canvas.getContext('2d');
const scoreElement=document.getElementById('score');
const gameOverElement=document.getElementById('gameOver');

//Game Constants
const gridSize=20;
const tileCount=canvas.width/ gridSize;

//Game Variables
let snake=[
    {x: Math.floor(tileCount/2), y: Math.floor(tileCount/2)}
];
let food={
    x: Math.floor(Math.random()* tileCount),
    y:Math.floor(Math.random()* tileCount)
};

let dx=1;
let dy=0;
let score=0;
let gameRunning=true;
gameOverElement.style.display='none';

//Game Loop
function gameLoop(){
    if (!gameRunning) return;

    setTimeout(()=>{
        requestAnimationFrame(gameLoop);
        updateGame();
        drawGame();
    }, 100); //Control game speed
}

//Update game state
function updateGame(){
    //Move snake
    const head={x: snake[0].x+dx,y: snake[0].y+dy};
    snake.unshift(head);

    //Check if food is eaten
    if(head.x === food.x && head.y === food.y){
        score+=10;
        scoreElement.textContent=`Score: ${score}`;
        generateFood(); // Corrected function name
    }else{
        snake.pop();
    }

    //Check for collisions
    checkCollisions();
}

//Draw game elements
function drawGame(){
    //Clear canvas
    ctx.fillStyle='white';
    ctx.fillRect(0, 0, canvas.width, canvas.height);

    //Draw snake
    ctx.fillStyle='green';
    snake.forEach(segment=>{
        ctx.fillRect(segment.x*gridSize, segment.y * gridSize, gridSize - 2, gridSize -2);

    });

    //Draw Food
    ctx.fillStyle='red';
    ctx.fillRect(food.x * gridSize, food.y * gridSize, gridSize -2, gridSize -2);

}

//Generate new food position
function generateFood(){
    food={
        x: Math.floor(Math.random()* tileCount),
        y: Math.floor(Math.random() * tileCount)
    };

    //Make Sure food doesn't spawn on snake
    while (snake.some(segment => segment.x === food.x && segment.y === food.y)){
        food={
            x: Math.floor(Math.random() * tileCount),
            y: Math.floor(Math.random()* tileCount)
        };
    }
}

//Check for collision
function checkCollisions(){
    const head= snake[0];

    //Wall collision
    if (head.x<0  || head.x >= tileCount || head.y <0 ||head.y >= tileCount){
        gameOver();
        return;
    }

    //Self collision
    for (let i=1; i< snake.length; i++){
        if (head.x === snake[i].x && head.y === snake[i].y){
            gameOver();
            return;
        }
    }
}

//Game Over function
function gameOver(){
    gameRunning=false;
    gameOverElement.style.display='block';
}

//Handle keyboard input
document.addEventListener('keydown', (event)=>{
    switch (event.key){
        case 'ArrowUp':
            if (dy === 0){dx=0; dy=-1;}
            break;
        case 'ArrowDown':
            if (dy ===0){dx=0; dy=1;}
            break;
        case 'ArrowLeft':
            if (dx ===0){dx=-1; dy=0;}
            break;
        case 'ArrowRight':
            if (dx ===0){dx=1; dy=0;} 
            break;   
    }
});

//Start game
gameLoop();
