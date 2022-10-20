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
        console.log(`DATA: ${position}`, player.style.left)

        player.style.left = position + 'px'
    }
)

window.addEventListener(
    'keydown',
    event => socket.emit(
        EVENTS.MOVEMENT,
        MOVEMENTS[event.code]
    )
)