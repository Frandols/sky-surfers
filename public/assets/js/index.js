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

console.log(document.querySelector('.container').width)

socket.on(
    EVENTS.POSITION,
    position => {
        player.style.left = position + 'px'

        console.log(player.style.left)
    }
)

window.addEventListener(
    'keydown',
    event => socket.emit(
        EVENTS.MOVEMENT,
        MOVEMENTS[event.code] ? MOVEMENTS[event.code] : 'none'
    )
)