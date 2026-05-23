.syntax unified
.thumb

.global JumpApp
.type JumpApp, %function

JumpApp:
    ldr sp, [r0, #0]
    ldr pc, [r0, #4]
