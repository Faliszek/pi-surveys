open Belt;

module Open = {
  open TW;
  [@react.component]
  let make =
      (
        ~id,
        ~text,
        ~allAnswers: array(SurveyForm.Solving.answer),
        ~onAnswerChange,
      ) => {
    let value =
      allAnswers
      ->Array.keep(a => a.question.id === id)
      ->Array.get(0)
      ->Option.flatMap(a => a.answer)
      ->Option.map(a => a.value)
      ->Option.getWithDefault("");

    <div className={[Margin(Mb12)]->make}>
      <Text className=[FontSize(TextLg)]> text </Text>
      <div className={[Margin(Mx12), Margin(My6)]->make}>
        <Input.Textarea value onChange={v => onAnswerChange(v)} />
      </div>
    </div>;
  };
};

module Choice = {
  open TW;
  [@react.component]
  let make =
      (
        ~id,
        ~text,
        ~answers: array(Survey.Answer.t),
        ~allAnswers: array(SurveyForm.Solving.answer),
        ~onAnswerChange,
      ) => {
    <div className={[Margin(Mb12)]->make}>
      <Text className=[FontSize(TextLg)]> text </Text>
      <div className={[Margin(Mx12), Margin(My6)]->make}>
        {answers
         ->Array.map(a => {
             let checked =
               allAnswers
               ->Array.keep(({question, answer}) =>
                   question.id === id
                   && answer
                      ->Option.map(x => x.id == a.id)
                      ->Option.getWithDefault(false)
                 )
               ->Array.get(0)
               ->Option.isSome;

             <div
               onClick={_ => onAnswerChange(a)}
               className={
                 [
                   Display(Flex),
                   Cursor(CursorPointer),
                   AlignItems(ItemsCenter),
                   Margin(Ml1),
                   Margin(My3),
                 ]
                 ->make
               }>
               <Checkbox
                 style={ReactDOMRe.Style.make(~marginRight="8px", ())}
                 checked
                 onChange=Js.log
               />
               <Text className=[FontSize(TextSm)]> {a.value} </Text>
             </div>;
           })
         ->React.array}
      </div>
    </div>;
  };
};

type action =
  | InitQuestions(array(Survey.Question.t))
  | ChangeOpenAnswer(string, string)
  | ChangeClosedAnswer(string, Survey.Answer.t);

let answerReducer = (state: array(SurveyForm.Solving.answer), action) => {
  switch (action) {
  | InitQuestions(questions) =>
    SurveyForm.Solving.answersFromquestions(questions)

  | ChangeOpenAnswer(questionId, value) =>
    state->Array.map(q =>
      q.question.id === questionId
        ? {...q, answer: q.answer->Option.map(a => {...a, value})} : q
    )

  | ChangeClosedAnswer(questionId, answer) =>
    state->Array.map(q =>
      q.question.id === questionId ? {...q, answer: Some(answer)} : q
    )
  };
};

module Step = {
  [@react.component]
  let make = (~title, ~subtitle, ~step, ~setStep) => {
    <div
      className=TW.(
        [
          Display(Flex),
          AlignItems(ItemsCenter),
          Margin(Mb12),
          JustifyContent(JustifyBetween),
        ]
        ->make
      )>
      <div
        className=TW.([Display(InlineFlex), AlignItems(ItemsCenter)]->make)>
        <div
          className=TW.(
            [
              Display(InlineFlex),
              Padding(P8),
              BorderRadius(RoundedFull),
              BoxShadow(ShadowLg),
              BackgroundColor(BgBlue100),
              Opacity(Opacity75),
            ]
            ->make
          )>
          {switch (step) {
           | 1 => <Icons.FileText size=48 color="#90cdf4" />
           | 2 => <Icons.UserCheck size=48 color="#90cdf4" />
           | 3 => <Icons.CheckCircle size=48 color="#90cdf4" />
           | _ => React.null
           }}
        </div>
        <div className=TW.([Margin(Ml8)]->make)>
          <div>
            {switch (step) {
             | 1 =>
               <>
                 <Text className=TW.[FontSize(Text2xl)]>
                   {j|Ankieta: |j}
                 </Text>
                 <Text className=TW.[FontSize(Text2xl)]> title </Text>
               </>
             | 2 =>
               <Text className=TW.[FontSize(Text2xl)]>
                 {j|Dane personalne |j}
               </Text>
             | _ => React.null
             }}
          </div>
          {switch (step) {
           | 1 =>
             <>
               <Text className=TW.[FontSize(TextXl)] color=`light>
                 {j|Opis: |j}
               </Text>
               <Text className=TW.[FontSize(TextXl)] color=`light>
                 subtitle
               </Text>
             </>
           | 2 =>
             <Text className=TW.[FontSize(TextXl)] color=`light>
               {j|Bez obaw, wyniki ankiety są anonimowe|j}
             </Text>
           | 3 =>
             <Text className=TW.[FontSize(TextXl)] color=`light>
               {j|Dziękujemy za wypełnienie ankiety!|j}
             </Text>

           | _ => React.null
           }}
        </div>
      </div>
      {switch (step) {
       | 3 => React.null
       | _ =>
         <div className=TW.([Display(Flex), AlignItems(ItemsCenter)]->make)>
           <div
             onClick={_ =>
               switch (step) {
               | 2 => setStep(1)
               | _ => ()
               }
             }
             className=TW.(
               [
                 Padding(P4),
                 Cursor(CursorPointer),
                 BorderRadius(RoundedFull),
                 BackgroundColor(
                   switch (step) {
                   | 2 => BgBlue100
                   | _ => BgGray100
                   },
                 ),
                 Margin(Mx4),
               ]
               ->make
             )>
             <Icons.ChevronLeft
               size=36
               color={step == 1 ? "#edf2f7" : "#90cdf4"}
             />
           </div>
           <div
             onClick={_ =>
               switch (step) {
               | 1 => setStep(2)
               | _ => ()
               }
             }
             className=TW.(
               [
                 Padding(P4),
                 Cursor(CursorPointer),
                 BorderRadius(RoundedFull),
                 BackgroundColor(
                   switch (step) {
                   | 1 => BgBlue100
                   | _ => BgGray100
                   },
                 ),
                 Margin(Mx4),
               ]
               ->make
             )>
             <Icons.ChevronRight
               size=36
               color={step == 1 ? "#90cdf4" : "#edf2f7"}
             />
           </div>
         </div>
       }}
    </div>;
  };
};

let getSolution = (~answers, ~name, ~email, ~number) => {
  let message = Js.Json.stringifyAny(answers)->Option.getWithDefault("{}");

  let key = name ++ email ++ number ++ Survey.generateHash();

  let crypt = Crypt.SHA512.encrypt(~message, ~key);

  crypt##toString();
};

[@react.component]
let make = (~id) => {
  let (data, _) = SurveySingleQuery.use(~id);

  let (solve, solveSurvey) = SurveySolveMutation.use();
  let (add, addSolution) = SurveySolveMutation.useAdd();

  let (questions: array(Survey.Question.t), setQuestions) =
    React.useState(() => [||]);

  let (allAnswers, setAllAnswers) = React.useReducer(answerReducer, [||]);
  let solution = Dom.Storage.getItem(id, Dom.Storage.localStorage);

  let (step, setStep) =
    React.useState(() =>
      switch (solution) {
      | Some(_) => 3
      | _ => 1
      }
    );

  let (name, setName) = React.useState(() => "");
  let (email, setEmail) = React.useState(() => "");
  let (number, setNumber) = React.useState(() => "");

  let notification = Notification.use();

  React.useEffect1(
    () => {
      switch (data.data) {
      | Some(data) =>
        let questions = SurveyForm.fromQuestions(data##form##questions);
        setQuestions(_ => questions);
        setAllAnswers(InitQuestions(questions));
      | None => ()
      };
      None;
    },
    [|data|],
  );

  let title =
    data.data->Option.map(d => d##form##title)->Option.getWithDefault("");
  let subtitle =
    data.data
    ->Option.flatMap(d => d##form##content)
    ->Option.getWithDefault("");

  <Layout padding=`big>
    <Step step setStep={s => setStep(_ => s)} title subtitle />
    <div className={TW.[Margin(My8), Margin(Mx8)]->TW.make}>
      {switch (step) {
       | 1 =>
         switch (data.response) {
         | Data(data) =>
           questions
           ->Array.map(q =>
               switch (q.type_) {
               | Open =>
                 <Open
                   id={q.id}
                   text={q.value}
                   allAnswers
                   onAnswerChange={v =>
                     setAllAnswers(ChangeOpenAnswer(q.id, v))
                   }
                 />
               | Rate(answers) =>
                 <Choice
                   id={q.id}
                   text={q.value}
                   answers
                   allAnswers
                   onAnswerChange={answer =>
                     setAllAnswers(ChangeClosedAnswer(q.id, answer))
                   }
                 />
               | Closed(answers) =>
                 <Choice
                   id={q.id}
                   text={q.value}
                   answers
                   allAnswers
                   onAnswerChange={answer =>
                     setAllAnswers(ChangeClosedAnswer(q.id, answer))
                   }
                 />
               }
             )
           ->React.array

         | Error(_) =>
           <Text>
             {j|Wystąpił błąd podczas łączenia się z serwerem|j}
           </Text>
         | Fetching => <Text> {j|Trwa wczytywanie danych|j} </Text>
         | NotFound => <Text> {j|Rekord o podanym ID nie istnieje|j} </Text>
         }

       | 2 =>
         <div>
           <div className=TW.([Margin(Mb8)]->make)>
             <Text className=TW.[Width(W32), Display(Block), Margin(Mb3)]>
               {j|Imię i nazwisko|j}
             </Text>
             <Input
               placeholder={j|Imię i nazwisko|j}
               value=name
               onChange={v => setName(_ => v)}
             />
           </div>
           <div className=TW.([Margin(Mb8)]->make)>
             <Text className=TW.[Width(W32), Display(Block), Margin(Mb3)]>
               {j|E-mail|j}
             </Text>
             <Input
               placeholder={j|E-mail|j}
               value=email
               onChange={v => setEmail(_ => v)}
             />
           </div>
           <div className=TW.([Margin(Mb8)]->make)>
             <Text className=TW.[Width(W32), Display(Block), Margin(Mb3)]>
               {j|Numer albumu|j}
             </Text>
             <Input
               placeholder={j|Numer albumu|j}
               value=number
               onChange={v => setNumber(_ => v)}
             />
           </div>
           <div
             className=TW.(
               [
                 Display(Flex),
                 AlignItems(ItemsCenter),
                 JustifyContent(JustifyCenter),
               ]
               ->make
             )>
             <Button
               onClick={_ => {
                 let solution =
                   getSolution(~answers=allAnswers, ~email, ~number, ~name);
                 solveSurvey(
                   ~solutionInput={
                     "name": name,
                     "email": email,
                     "number": number,
                     "surveyId": id,
                     "solution": solution,
                   },
                   (),
                 )
                 |> Js.Promise.then_(_ => {
                      Dom.Storage.setItem(
                        id,
                        solution,
                        Dom.Storage.localStorage,
                      );
                      setStep(_ => 3);

                      notification.show(
                        `success,
                        {j|Pomyślnie wysłano ankietę!|j},
                      );
                      addSolution(
                        ~formInput={
                          "title": title,
                          "questions":
                            Some(
                              allAnswers->SurveyForm.Solving.answersToRequest,
                            ),
                          "parentId": Some(id),
                          "content": subtitle,
                        },
                        (),
                      );
                    })
                 |> ignore;
               }}
               loading={solve.fetching}>
               <Text color=`white> {j|WYŚLIJ|j} </Text>
             </Button>
           </div>
         </div>
       | 3 =>
         <div>
           <Text className=TW.[FontSize(TextSm)] color=`light>
             {j|Poniżej znajdziesz swój kod ankiety, proszę zachowaj go w bezpiecznym miejscu,|j}
           </Text>
           <br />
           <Text className=TW.[FontSize(TextSm)] color=`light>
             {j|kod ten aby zapewnić ci 100% anonimowość nie będzie nigdzie przechowywany, będzie Ci on potrzebny,|j}
           </Text>
           <br />
           <Text className=TW.[FontSize(TextSm)] color=`light>
             {j| jeśli będziesz chciał sprawdzić rozwiązanie swojej ankiety na innym urządzeniu|j}
           </Text>
           <br />
           <br />
           <Text
             className=TW.[FontSize(TextSm), FontWeight(FontBold)]
             color=`light>
             {j|UWAGA!|j}
           </Text>
           <Text className=TW.[FontSize(TextSm)] color=`light>
             {j| W celach bezpieczeństwa pokazujemy tylko część kodu, aby pobrać cały kod kliknij w przycisk,|j}
           </Text>
           <Text
             color=`light
             className=TW.[FontSize(TextSm), FontWeight(FontBold)]>
             {j| SKOPIUJ|j}
           </Text>
           <br />
           <br />
           <Text
             className=TW.[FontSize(TextLg), WordBreak(BreakAll)]
             color=`light>
             {solution
              ->Option.map(s =>
                  Js.String.slice(~from=0, ~to_=32, s) ++ " ..."
                )
              ->Option.getWithDefault("")}
           </Text>
           <br />
           <br />
           <Button
             onClick={_ => {
               Survey.copyToClipboard(solution) |> ignore;
               notification.show(`success, {j|Skopiowano kod!|j});
             }}>
             <Text color=`white> {j|SKOPIUJ|j} </Text>
           </Button>
         </div>
       | _ => React.null
       }}
    </div>
  </Layout>;
};