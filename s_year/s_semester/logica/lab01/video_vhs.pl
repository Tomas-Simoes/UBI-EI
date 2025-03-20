video(jvc,d540,vhs,mono,uma_velocidade,n_insert,n_pip,n_dobragem_audio).
video(jvc,fc100,vhs,mono,dupla_velocidade,n_insert,n_pip,n_dobragem_audio).
video(jvc,d830,vhs,stereo,dupla_velocidade,n_insert,n_pip,dobragem_audio).
video(jvc,d960,vhs,stereo,dupla_velocidade,insert,n_pip,dobragem_audio).
video(jvc,s5800,s_vhs,stereo,dupla_velocidade,insert,n_pip,dobragem_audio).
video(sanyo,vhr8100,vhs,mono,uma_velocidade,n_insert,n_pip,n_dobragem_audio).
video(sanyo,vhr8500,vhs,mono,dupla_velocidade,n_insert,n_pip,n_dobragem_audio).
video(sanyo,vhr8700,vhs,stereo,dupla_velocidade,n_insert,n_pip,n_dobragem_audio).
video(sanyo,vhr4890,vhs,stereo,dupla_velocidade,insert,pip,dobragem_audio).
video(grundig,vs630,vhs,mono,uma_velocidade,n_insert,n_pip,n_dobragem_audio).
video(grundig,vs810,vhs,mono,uma_velocidade,insert,n_pip,n_dobragem_audio).
video(grundig,vs660,vhs,stereo,dupla_velocidade,n_insert,n_pip,n_dobragem_audio).
video(grundig,vs680,s_vhs,stereo,dupla_velocidade,insert,pip,dobragem_audio). 

/* 
Questions:  
    ? video(S, _, s_vhs, _, _, _, _ ,_ ) -> S=jvc, S=grundig
    ? video(S, M, vhs, stereo, dupla_velocidade, insert, _ ,_ ) -> {S=jvc, M=d960}, {S=sanyo, M=vhr4890} 
*/
