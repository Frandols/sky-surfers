const socket = io.connect('http://localhost:5000')
const container = document.querySelector('.container')
const player = document.querySelector('.player')

class Enemy {
    constructor(position) {
        this.position = position
    }

    deploy() {
        const enemy = document.createElement('div')

        enemy.className = 'enemy'
        enemy.style.left = this.position + 'px'

        container.appendChild(enemy)

        setTimeout(
            () => container.removeChild(enemy),
            5 * 1000
        )
    }
}

const EVENTS = {
    POSITION: 'position',
    MOVEMENT: 'movement',
    ENEMY: 'enemy'
}

const MOVEMENTS = {
    ArrowRight: 'right',
    ArrowLeft: 'left'
}

socket.on(
    EVENTS.POSITION,
    position => {
        player.style.left = position + 'px'

        player.classList.remove('step')
    }
)

socket.on(
    EVENTS.ENEMY,
    position => {
        const enemy = new Enemy(position)

        enemy.deploy()
    }
)

window.addEventListener(
    'keydown',
    event => {
        player.classList.add('step')

        MOVEMENTS[event.code] 
        && socket.emit(
            EVENTS.MOVEMENT,
            MOVEMENTS[event.code]
        )
    }
)