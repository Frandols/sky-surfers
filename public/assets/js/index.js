const socket = io.connect('http://localhost:5000')
const player = document.querySelector('.player')

const EVENTS = {
    DATA: 'data'
}

const MOVEMENTS = {
    ArrowRight: 'right',
    ArrowLeft: 'left'
}

socket.on(
    EVENTS.DATA,
    (data) => {
        console.log(`DATA: ${data}`, player.style.left)

        player.style.left = `${Number(data)}px`
    }
)

window.addEventListener(
    'keydown',
    event => socket.emit(
        EVENTS.DATA,
        MOVEMENTS[event.code]
    )
)