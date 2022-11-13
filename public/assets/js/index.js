const socket = io.connect('http://localhost:5000')

const root = document.querySelector(':root')
const container = document.querySelector('.container')
const player = document.querySelector('.player')

class Bullet {
    node = null

    constructor({ shooter }) {
        this.shooter = shooter
    }

    deploy() {
        this.node = document.createElement('div')
        this.node.className = 'bullet'

        this.node.style.setProperty(
            'left',
            `${this.shooter.node.offsetLeft}px`
        )
        this.node.style.setProperty(
            'top',
            `${this.shooter.node.offsetTop}px`
        )
        
        container.appendChild(this.node)

        const h = 1200
        const a = player.offsetLeft - this.shooter.node.offsetLeft
        const b = player.offsetTop - this.shooter.node.offsetTop
        const angle = Math.atan(a / b)

        this.node.style.setProperty(
            'transform', 
            `translate(${h * Math.sin(angle)}px, ${h * Math.cos(angle)}px)`
        )

        setTimeout(
            () => this.destroy(),
            1.5 * 1000
        )
    }

    destroy() {
        container.removeChild(this.node)
    }
}

class Enemy {
    node = null
    ammunitionCount = 1

    constructor({ position }) {
        this.position = position
    }

    deploy() {
        this.node = document.createElement('div')
        this.node.className = 'enemy'

        this.node.style.setProperty(
            'left',
            `${this.position}px`
        )

        container.appendChild(this.node)

        this.shoot()

        setTimeout(
            () => this.destroy(),
            5 * 1000
        )
    }

    shoot() {
        const bullet = new Bullet({ shooter: this })

        bullet.deploy()

        const shooting = setInterval(
            () => {
                if(this.ammunitionCount === 0) return clearInterval(shooting)

                bullet.deploy()

                this.ammunitionCount--
            },
            1.5 * 1000
        )
    }

    destroy() {
        container.removeChild(this.node)
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
        const enemy = new Enemy({ position })

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