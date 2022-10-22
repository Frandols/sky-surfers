const socket = io.connect('http://localhost:5000')
const player = document.querySelector('.player')

const EVENTS = {
    POSITION: 'position',
    MOVEMENT: 'movement'
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