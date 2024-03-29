const size = 500;
let eaten_apples = 0;

window.onload = function() {
    let canvas = document.getElementsByTagName('canvas')[0];
    statusLabel = document.getElementsByName('status')[0];

    canvas.height = size;
    canvas.width = size;

    context = canvas.getContext('2d');
    context.fillStyle = 'black';
    context.fillRect(0, 0, size, size);

    // read policy from file
    document.getElementById('file').onchange = function(){
        const file = this.files[0];
        const reader = new FileReader();

        reader.onload = function(progressEvent){
            const lines = this.result.split('\n');
            const height = lines.length-1;
            const width = lines[0].split(' ').length-1;

            let policy = Array(height).fill(0).map(x => Array(width).fill(0));

            let x = 0;
            let y = 0;
            for (const line of lines) {
                let actions = line.split(' ');
                for (const action of actions) {
                    if (action === '') {
                        x += 1;
                        y = 0;
                        continue;
                    }
                    // flip x and y
                    policy[y][x] = action;
                    y += 1;
                }
            }
            initGame(policy);
            setInterval(play, 200);
        };
        reader.readAsText(file);
    };
}

function initGame(p) {
    policy = p;
    boardWidth = Math.ceil(policy.length/2);
    boardHeight = Math.ceil(policy[0].length/2);
    maxSteps = boardWidth + boardHeight; // reset after this number of steps
    resetGame();
}

function resetGame() {
    snake = {
        x: getRandomInt(0, boardWidth),
        y: getRandomInt(0, boardHeight)
    }
    resetApple();
    state = {
        x_distance: snake.x - apple.x,
        y_distance: snake.y - apple.y
    }
}

function resetApple() {
    steps = 0;
    apple = {
        x: getRandomInt(0, boardWidth),
        y: getRandomInt(0, boardHeight)
    }
}

function performAction() {
    steps += 1;
    if (snake.x < 0 || snake.y < 0 || snake.x >= boardWidth || snake.y >= boardHeight) {
        statusLabel.textContent = 'Snake left the board! Restarting...';
        resetGame();
    }
    if (steps > maxSteps) {
        statusLabel.textContent = 'Snake is stuck! Restarting...';
        resetGame();
    }

    if (action === 'U') {
        snake.y -= 1;
    } else if (action === 'D') {
        snake.y += 1;
    } else if (action === 'L') {
        snake.x -= 1;
    } else if (action === 'R') {
        snake.x += 1;
    } else if (action === 'X') {
        eaten_apples += 1;
        statusLabel.textContent = 'Ate ' + eaten_apples + ' apples!';
        resetApple();
    }

    state.x_distance = snake.x - apple.x;
    state.y_distance = snake.y - apple.y;
}

function play() {
    paint();
    getAction();
    performAction();
}

function paint() {
    context.fillStyle = 'black';
    context.fillRect(0, 0, size, size);

    context.fillStyle = 'green';
    context.fillRect(apple.x * (size/boardWidth), apple.y * (size/boardHeight), (size/boardWidth), (size/boardHeight));
    context.fillStyle = 'red';
    context.fillRect(snake.x * (size/boardWidth), snake.y * (size/boardHeight), (size/boardWidth), (size/boardHeight));
}

function getAction() {
    const x = state.x_distance + boardWidth-1;
    const y = state.y_distance + boardHeight-1;
    try {
        action = policy[x][y];
    } catch {
        resetGame();
    }
}

// from https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Math/random 
function getRandomInt(min, max) {
    min = Math.ceil(min);
    max = Math.floor(max);
    return Math.floor(Math.random() * (max - min)) + min; // the maximum is exclusive and the minimum is inclusive
}
